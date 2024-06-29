//Description: Defines Groovy script functions for Jenkins pipeline

def getUserConfirmation(message) {
  input message: message // Prompt the user for confirmation with a custom message
}

def build() {
  getUserConfirmation('Proceed with build?') // Prompt user to proceed with the build stage
  echo 'Executing Build Phase' 
  echo 'Files in current folder:'
  sh 'ls' // List the files in the current directory
}

def test() {
  getUserConfirmation('Proceed with test?') // Prompt user to proceed with the test stage
  echo 'Executing Test Phase' 
  dir('..') { // Change to the parent directory
    echo 'Changed to folder:' 
    sh 'pwd' // Print the current working directory
    echo 'Files in folder:' 
    sh 'ls' // List the files in the current directory
  }
  echo 'Returned to folder:' 
  sh 'pwd' // Print the original working directory
}

def deploy() {
  getUserConfirmation('Proceed with deploy?') // Prompt user to proceed with the deploy stage
  echo 'Executing Deploy Phase'

  echo 'Showing git status:'
  sh 'git status' // Show the current status of the git repository

  echo 'Showing selected environment variables:'
  sh '''
    echo "JENKINS_HOME: $JENKINS_HOME"
    echo "BRANCH_NAME: $BRANCH_NAME"
    echo "GIT_COMMIT: $GIT_COMMIT"
    echo "GIT_BRANCH: $GIT_BRANCH"
    echo "BUILD_NUMBER: $BUILD_NUMBER"
    echo "JOB_NAME: $JOB_NAME"
  ''' // Print selected environment variables

  echo 'Showing run time:'
  sh 'uptime' // Show the system uptime
}

return this // Return the script's context to be used by the Jenkinsfile

