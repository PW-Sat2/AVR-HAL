node('linux') {
	stage 'checkout'
	checkout scm
	stage 'checkStyle'
	sh 'ls -ahrl'
	sh 'make checkStyle'
}