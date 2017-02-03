node('linux') {
	stage 'checkout'
	deleteDir()
	checkout scm
	stage 'clean'
	
	withEnv(["HAL_PATH=${pwd()}/HAL"]) {
		
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
}
