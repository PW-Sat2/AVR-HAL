node('linux') {
	stage 'checkout '
	checkout scm
	stage 'checkStyle'
	sh 'make checkStyle'
	stage 'compile examples'
	sh 'make -C examples all'
}
