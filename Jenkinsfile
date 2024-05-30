def execute
pipeline {

  agent any
  
  stages {
    stage("start") {
      steps {
        script {
          execute = load "pipeline_steps.groovy"
        }
      }
    }
    
    stage("build") {
      steps {
        script {
          execute.build()
        }
      }
    }

    stage("test") {
      steps {
        script {
          execute.test()
        }
      }
    }

    stage("deploy") {
      steps {
        script {
          execute.deploy()
        }
      }
    }
  }
}
