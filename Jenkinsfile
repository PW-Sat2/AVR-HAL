node('linux') {
	stage 'checkout'
	sh 'export HAL_PATH=$(pwd)/HAL'
	checkout scm
	stage 'clean'
	sh 'make clean'
	sh 'make -C examples clean'
	sh 'make -C unit_tests clean'
	stage 'checkStyle'
	sh 'make checkStyle'
	stage 'compile examples'
	sh 'make -C examples all'
	stage 'unit tests'
	sh 'make -C unit_tests all'
}
