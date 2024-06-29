//Description: This Jenkinsfile defines the Jenkins pipeline, which comprises the build, test, and deploy stages for an application. Each stage currently executes shell commands as placeholders for future needs.

pipeline {
  agent any

  stages {
    stage("start") {
      steps {
        script {
          // Load the Groovy script that contains the steps for each stage
          execute = load "pipeline_steps.groovy"
        }
      }
    }

    stage("build") {
      steps {
        script {
          // Execute the build method from the loaded Groovy script
          execute.build()
        }
      }
    }

    stage("test") {
      steps {
        script {
          // Execute the test method from the loaded Groovy script
          execute.test()
        }
      }
    }

    stage("deploy") {
      steps {
        script {
          // Execute the deploy method from the loaded Groovy script
          execute.deploy()
        }
      }
    }
  }
}
