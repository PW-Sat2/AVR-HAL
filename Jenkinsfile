node('linux') {
	stage 'checkout'
	checkout scm
	stage 'clean'
	
	env.HAL_PATH = "/home/jenkins/workspace/AVR-HAL/devel/HAL"
	sh "env"
	
	sh "echo $HAL_PATH"
	sh "ls $HAL_PATH"
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
