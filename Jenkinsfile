node('linux') {
	stage 'checkout'
	checkout scm
	stage 'checkStyle'
	sh 'make checkStyle'
	stage 'examples'
	sh 'make -C examples all_targets'
}
