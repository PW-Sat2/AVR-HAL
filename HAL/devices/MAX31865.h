#ifndef HAL_DEVICES_MAX31865_H_
#define HAL_DEVICES_MAX31865_H_

#include "SPI.h"
#include "DigitalIO.h"
#include "array.h"
#include <util/delay.h>

#define MAX31865_FAULT_HIGH_THRESHOLD  ( 1 << 7 )
#define MAX31865_FAULT_LOW_THRESHOLD   ( 1 << 6 )
#define MAX31865_FAULT_REFIN           ( 1 << 5 )
#define MAX31865_FAULT_REFIN_FORCE     ( 1 << 4 )
#define MAX31865_FAULT_RTDIN_FORCE     ( 1 << 3 )
#define MAX31865_FAULT_VOLTAGE         ( 1 << 2 )

#define MAX31865_FAULT_DETECTION_NONE      ( 0x00 << 2 )
#define MAX31865_FAULT_DETECTION_AUTO      ( 0x01 << 2 )
#define MAX31865_FAULT_DETECTION_MANUAL_1  ( 0x02 << 2 )
#define MAX31865_FAULT_DETECTION_MANUAL_2  ( 0x03 << 2 )



/* RTD data, RTD current, and measurement reference
   voltage. The ITS-90 standard is used; other RTDs
   may have coefficients defined by the DIN 43760 or
   the U.S. Industrial (American) standard. */
#define RTD_A_ITS90         3.9080e-3
#define RTD_A_USINDUSTRIAL  3.9692e-3
#define RTD_A_DIN43760      3.9848e-3
#define RTD_B_ITS90         -5.870e-7
#define RTD_B_USINDUSTRIAL  -5.8495e-7
#define RTD_B_DIN43760      -5.8019e-7
/* RTD coefficient C is required only for temperatures
   below 0 deg. C.  The selected RTD coefficient set
   is specified below. */
#define SELECT_RTD_HELPER(x) x
#define SELECT_RTD(x) SELECT_RTD_HELPER(x)
#define RTD_A         SELECT_RTD(RTD_A_ITS90)
#define RTD_B         SELECT_RTD(RTD_B_ITS90)
/*
 * The reference resistor on the hardware; see the MAX31865 datasheet
 * for details.  The values 400 and 4000 Ohm are recommended values for
 * the PT100 and PT1000.
 */
#define RTD_RREF_PT100         400 /* Ohm */
#define RTD_RREF_PT1000       4990 /* Ohm */
/*
 * The RTD resistance at 0 degrees Celcius.  For the PT100, this is 100 Ohm;
 * for the PT1000, it is 1000 Ohm.
 */
#define RTD_RESISTANCE_PT100   100 /* Ohm */
#define RTD_RESISTANCE_PT1000 1000 /* Ohm */

#define RTD_ADC_RESOLUTION  ( 1u << 15 ) /* 15 bits */


namespace hal {

class MAX31865 {
 public:

    enum ptd_type { RTD_PT100, RTD_PT1000 };

    explicit MAX31865(DigitalIO::Pin pin_cs, uint16_t refResistor) : spi_dev(pin_cs), refResistor(refResistor) {
    }

    void init() const {
      this->spi_dev.disable();
    }

    /**
     * Configure the MAX31865.  The parameters correspond to Table 2 in the MAX31865
     * datasheet.  The parameters are combined into a control bit-field that is stored
     * internally in the class for later reconfiguration, as are the fault threshold values.
     *
     * @param [in] v_bias Vbias enabled (@a true) or disabled (@a false).
     * @param [in] conversion_mode Conversion mode auto (@a true) or off (@a false).
     * @param [in] one_shot 1-shot measurement enabled (@a true) or disabled (@a false).
     * @param [in] three_wire 3-wire enabled (@a true) or 2-wire/4-wire (@a false).
     * @param [in] fault_detection Fault detection cycle control (see Table 3 in the MAX31865
     *             datasheet).
     * @param [in] fault_clear Fault status auto-clear (@a true) or manual clear (@a false).
     * @param [in] filter_50hz 50 Hz filter enabled (@a true) or 60 Hz filter enabled
     *             (@a false).
     * @param [in] low_threshold Low fault threshold.
     * @param [in] high_threshold High fault threshold.
    */
    void configure( bool v_bias, bool conversion_mode, bool one_shot,
                    bool three_wire, uint8_t fault_cycle, bool fault_clear,
                    bool filter_50hz, uint16_t low_threshold,
                    uint16_t high_threshold ) {

        uint8_t control_bits = 0;

        /* Assemble the control bit mask. */
        control_bits |= ( v_bias ? 0x80 : 0 );
        control_bits |= ( conversion_mode ? 0x40 : 0 );
        control_bits |= ( one_shot ? 0x20 : 0 );
        control_bits |= ( three_wire ? 0x10 : 0 );
        control_bits |= fault_cycle & 0b00001100;
        control_bits |= ( fault_clear ? 0x02 : 0 );
        control_bits |= ( filter_50hz ? 0x01 : 0 );

        /* Store the control bits and the fault threshold limits for reconfiguration
           purposes. */
        this->configuration_control_bits   = control_bits;
        this->configuration_low_threshold  = low_threshold;
        this->configuration_high_threshold = high_threshold;
        
        /* Perform an full reconfiguration */
        reconfigure( true );
    }

    /**
     * ReConfigure the MAX31865.  The parameters correspond to Table 2 in the MAX31865
     * datasheet.  The parameters use other control bit-field that is stored internally 
     * in the class and change only new values
     *
     * @param [in] v_bias Vbias enabled (@a true) or disabled (@a false).
     * @param [in] conversion_mode Conversion mode auto (@a true) or off (@a false).
     * @param [in] one_shot 1-shot measurement enabled (@a true) or disabled (@a false).
     * @param [in] fault_detection Fault detection cycle control (see Table 3 in the MAX31865
     *             datasheet).
    */
    void configure( bool v_bias, bool conversion_mode, bool one_shot, uint8_t fault_cycle ) {
      /* Use the stored the control bits, and set new ones only */
      this->configuration_control_bits &= ~ (0x80 | 0x40 | 0x20 | 0b00001100);

      this->configuration_control_bits |= ( v_bias ? 0x80 : 0 );
      this->configuration_control_bits |= ( conversion_mode ? 0x40 : 0 );
      this->configuration_control_bits |= ( one_shot ? 0x20 : 0 );
      this->configuration_control_bits |= fault_cycle & 0b00001100;

      /* Perform light configuration */
      reconfigure(false);
    }


/**
 * Reconfigure the MAX31865 by writing the stored control bits and the stored fault
 * threshold values back to the chip.
 *
 * @param [in] full true to send also threshold configuration
 */ 
void reconfigure(bool full) {
  /* Write the threshold values. */
  if (true == full) {
    uint16_t threshold ;

    this->spi_dev.enable();
    spi_dev.shift( 0x83 );
    threshold = this->configuration_high_threshold ;
    spi_dev.shift( ( threshold >> 8 ) & 0x00ff );
    spi_dev.shift(   threshold        & 0x00ff );
    threshold = this->configuration_low_threshold ;
    spi_dev.shift( ( threshold >> 8 ) & 0x00ff );
    spi_dev.shift(   threshold        & 0x00ff );
    this->spi_dev.disable();
  }

  /* Write the configuration to the MAX31865. */
  this->spi_dev.enable();
  spi_dev.shift( 0x80 );
  spi_dev.shift( this->configuration_control_bits );
  this->spi_dev.disable();
}

/**
 * Apply the Callendar-Van Dusen equation to convert the RTD resistance
 * to temperature:
 *
 *   \f[
 *   t=\frac{-A\pm \sqrt{A^2-4B\left(1-\frac{R_t}{R_0}\right)}}{2B}
 *   \f],
 *
 * where
 *
 * \f$A\f$ and \f$B\f$ are the RTD coefficients, \f$R_t\f$ is the current
 * resistance of the RTD, and \f$R_0\f$ is the resistance of the RTD at 0
 * degrees Celcius.
 *
 * For more information on measuring with an RTD, see:
 * <http://newton.ex.ac.uk/teaching/CDHW/Sensors/an046.pdf>.
 *
 * @param [in] resistance The measured RTD resistance.
 * @return Temperature in degrees Celcius.
 */
double temperature() const
{
  static const double a2   = 2.0 * RTD_B;
  static const double b_sq = RTD_A * RTD_A;

  const double rtd_resistance =
    ( this->type == RTD_PT100 ) ? RTD_RESISTANCE_PT100 : RTD_RESISTANCE_PT1000;

  double c = 1.0 - resistance() / rtd_resistance;
  double D = b_sq - 2.0 * a2 * c;
  double temperature_deg_C = ( -RTD_A + sqrt( D ) ) / a2;

  return temperature_deg_C;
}

/**
 * Read all settings and measurements from the MAX31865 and store them
 * internally in the class.
 *
 * @return Fault status byte
 */
uint8_t read_all() {
  uint16_t combined_bytes;

  /* Start the read operation. */
  this->spi_dev.enable();
  /* Tell the MAX31865 that we want to read, starting at register 0. */
  spi_dev.shift( 0x00 );

  /* Read the MAX31865 registers in the following order:
       Configuration
       RTD
       High Fault Threshold
       Low Fault Threshold
       Fault Status */

  this->measured_configuration = spi_dev.shift( 0x00 );

  combined_bytes  = spi_dev.shift( 0x00 ) << 8;
  combined_bytes |= spi_dev.shift( 0x00 );
  this->measured_resistance = combined_bytes >> 1;

  combined_bytes  = spi_dev.shift( 0x00 ) << 8;
  combined_bytes |= spi_dev.shift( 0x00 );
  this->measured_high_threshold = combined_bytes ;

  combined_bytes  = spi_dev.shift( 0x00 ) << 8;
  combined_bytes |= spi_dev.shift( 0x00 );
  this->measured_low_threshold = combined_bytes ;

  this->measured_status = spi_dev.shift( 0x00 );

  this->spi_dev.disable();

  /* Reset the configuration if the measured resistance is
     zero or a fault occurred. */
  if(   this->measured_resistance == 0 || this->measured_status != 0  )
    reconfigure( true );

  return( status() );
}

/**
 * Read fault status
 * internally in the class.
 *
 * @return Fault status byte
 */
uint8_t fault_status() {
  /* Start the read operation. */
  this->spi_dev.enable();
  /* Tell the MAX31865 that we want to read, starting at register 7. */
  spi_dev.shift( 0x07 );
  uint8_t fault_status = this->measured_status = spi_dev.shift( 0x00 );
  this->spi_dev.disable();
  return( fault_status );
}

/**
 * Read configuration register
 * internally in the class.
 *
 * @return config register byte
 */
uint8_t config_register() {
  this->spi_dev.enable();
  /* Tell the MAX31865 that we want to read, starting at register 0. */
  spi_dev.shift(0x00);
  uint8_t config_register = this->measured_status = spi_dev.shift(0x00);
  this->spi_dev.disable();

  return config_register;
}


uint8_t status( ) const { return( measured_status ); }
  uint16_t low_threshold( ) const { return( measured_low_threshold ); }
  uint16_t high_threshold( ) const  { return( measured_high_threshold ); }
  uint16_t raw_resistance( ) const { return( measured_resistance ); }
  double resistance( ) const
  {
    const double rtd_rref =
      ( this->type == RTD_PT100 ) ? (double)RTD_RREF_PT100 : (double)RTD_RREF_PT1000;
    return( (double)raw_resistance( ) * rtd_rref / (double)RTD_ADC_RESOLUTION );
  }

 private:
    const SPI_Device spi_dev;
    const uint16_t refResistor;

    /* Our configuration. */
    uint8_t  cs_pin;
    ptd_type type;
    uint8_t  configuration_control_bits;
    uint16_t configuration_low_threshold;
    uint16_t configuration_high_threshold;
    void reconfigure( );

    /* Values read from the device. */
    uint8_t  measured_configuration;
    uint16_t measured_resistance;
    uint16_t measured_high_threshold;
    uint16_t measured_low_threshold;
    uint8_t  measured_status;
};

}  // namespace hal

#endif  // HAL_DEVICES_MAX31865_H_
