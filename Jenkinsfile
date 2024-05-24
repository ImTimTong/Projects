CODE_CHANGES = getGitChanges()
def gv
pipeline {

  agent any
  parameters {
    choice(name: 'VERSION', choices['1.1.0','1.2.0','1.3.0'], description: '')
    booleanPram(name: 'executeTests', defaultValue: true, description: '')
  }
  
  stages {
    stage("init") {
      steps {
        steps {
          script {
            gv = load "script.groovy"
          }
        }
      }
    }
    
    stage("build") {
      steps {
        script {
          gv.initApp()
        }
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
