pipeline {

  triggers {
    pollSCM('') // Enabling being build on Push
  }
  
  agent any

  stages {

    stage("build") {

      steps {
        echo 'building the app...'
      }
    }

    stage("test") {

      steps {
        echo 'testing the app...'
      }
    }

    stage("deploy") {

      steps {
        echo 'deploying the app...'
      }
    }
  }
}
