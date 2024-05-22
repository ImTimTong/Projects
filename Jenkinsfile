CODE_CHANGES = getGitChanges()
pipeline {

  agent any
  parameters {
    string(name: 'VERSION', defaultValue: '', description: 'version to deploy on prod')
    choice(name: 'VERSION', choices['1.1.0','1.2.0','1.3.0'], description: '')
    booleanPram(name: 'executeTests', defaultValue: true, description: '')
  }
  tools {
    maven 'Maven'
    gradle
    jdk
  }
  environment {
    NEW_VERSION = '1.3.0'
    SERVER_CREDENTIALS = credentials('server-credentials')
  }

  stages {

    stage("build") {
      when {
        expression {
          BRANCH_NAME == 'dev' && CODE_CHANGES == true 
        }
      }
      steps {
        echo '...building the app...'
        echo "building version ${NEW_VERSION}"
        echo 'building version ${NEW_VERSION}'
        sh "mvn install"
      }
    }

    stage("test") {
      when {
        expression {
          params.executeTests || BRANCH_NAME == 'dev' || BRANCH_NAME == 'main' 
        }
      }
      steps {
        echo 'testing the app...'
      }
    }

    stage("deploy") {

      steps {
        echo 'deploying the app...'
        echo "deploying version ${VERSION}"
        withCredentials([
          usernamePassword(credentials: 'server-credentials', usernameVariable: USER, passwordVariable: PWD)
        ]) {
          sh "some script ${USER} ${PWD}"
        }
        echo "deploying with ${SERVER_CREDENTIALS}"
        sh "${SERVER_CREDENTIALS}"
      }
    }
  }
  post {
    always {
      //
    }
    failure {
      
    }
    success {
    
    }
  }
}
