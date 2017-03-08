node('linux') {
	stage 'checkout'
	deleteDir()
	checkout scm
	
	stage 'clean'
	sh 'make clean'
	
	stage 'checkStyle'
	sh 'make checkStyle'

	stage 'compile examples'
	sh 'make examples'

	stage 'unit tests'
	sh 'make unit_tests_run'
}
