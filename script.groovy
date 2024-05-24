def buildApp() {
  echo 'build app'
}

def testApp() {
  echo 'test app'
}

def deployApp() {
  echo 'deploying the app...'
  echo "deploying version ${params.VERSION}"
}

return this
