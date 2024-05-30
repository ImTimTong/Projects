def getUserConfirmation(message) {
  input message: message
}

def build() {
  getUserConfirmation('Proceed with build?')
  echo 'Executing Build Phase'
  echo 'Files in current folder:'
  sh 'ls'
}

def test() {
  getUserConfirmation('Proceed with test?')
  echo 'Executing Test Phase'
  dir('..') {
    echo 'Changed to folder:'
    sh 'pwd'
    echo 'Files in folder:'
    sh 'ls'
  }
  echo 'Returned to folder:'
  sh 'pwd'
}

def deploy() {
  getUserConfirmation('Proceed with deploy?')
  echo 'Executing Deploy Phase'
  
  echo 'Showing git status:'
  sh 'git status'
  
  echo 'Showing environment variables:'
  sh 'printenv'

  echo 'Showing run time:'
  sh 'uptime'
}

return this
