CODE_CHANGES = getGitChanges()
pipeline {

  agent any
  parameters {
    choice(name: 'VERSION', choices['1.1.0','1.2.0','1.3.0'], description: '')
    booleanPram(name: 'executeTests', defaultValue: true, description: '')
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
        echo "deploying version ${params.VERSION}"
        withCredentials([
          usernamePassword(credentials: 'server-credentials', usernameVariable: USER, passwordVariable: PWD)
        ]) {
          echo "deploying with ${USER} ${PWD}"
        }
      }
    }
  }
}
