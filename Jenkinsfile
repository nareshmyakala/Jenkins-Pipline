pipeline {
  agent any
  stages {
    stage('Build') {
      parallel {
        stage('Build') {
          steps {
            echo 'Pipline build'
          }
        }

        stage('MISRA chat') {
          steps {
            echo 'MISRA chat'
          }
        }

      }
    }

    stage('Deploy') {
      parallel {
        stage('Deploy') {
          steps {
            echo 'Pipeline Deploy'
          }
        }

        stage('Unit test') {
          steps {
            echo 'Unit test'
          }
        }

      }
    }

    stage('Live Test') {
      steps {
        echo 'Pipeline Live test'
      }
    }

  }
}