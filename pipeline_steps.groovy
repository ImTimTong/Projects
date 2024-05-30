def getUserConfirmation(message) {
  input message: message
}

def build() {
  getUserConfirmation('Proceed with build?')
  echo 'Executing Build Phase'
}

def test() {
  getUserConfirmation('Proceed with test?')
  echo 'Executing Test Phase'
}

def deploy() {
  getUserConfirmation('Proceed with deploy?')
  echo 'Executing Deploy Phase'
}

return this
