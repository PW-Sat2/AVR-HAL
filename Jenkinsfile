node('linux') {
	stage 'checkout'
	deleteDir()
	checkout scm
	
	stage 'clean'
	sh 'make clean'
	
	stage 'compile examples'
	sh 'make examples'

	stage 'unit tests'
	sh 'make unit_tests_run'

	stage 'SingleDeviceTests'
	sh 'make SingleDeviceTests'	

	stage 'checkStyle'
	sh 'make checkStyle'
	
	stage 'checkFormat'
	sh 'make checkFormat'
}
