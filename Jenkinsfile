pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                script {
                    // Customize CMake configuration options based on Jenkins parameters or your requirements
                    def cmakeOptions = "-DMOCK_GL=ON -DMOCK_APPDATA=ON"
                    sh "cmake . -Bbuild ${cmakeOptions}"
                    sh "cmake --build build"
                }
            }
        }


        stage('Test') {
            steps {
                script {
                    cmakeBuild(buildDir: 'build', targets: 'test')
                }
            }
        }

        stage('SonarQube Analysis') {
            steps {
                script {
                    withSonarQubeEnv('SonarQubeServer') {
                        cmakeBuild(buildDir: 'build', targets: 'sonar')
                    }
                }
            }
        }

        stage('Snyk Security Scan') {
            steps {
                script {
                    // Add Snyk scan command here
                }
            }
        }
    }
}
