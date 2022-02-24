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
      steps {
        echo 'Pipeline Deploy'
      }
    }

    stage('Live Test') {
      steps {
        echo 'Pipeline Live test'
      }
    }

  }
}