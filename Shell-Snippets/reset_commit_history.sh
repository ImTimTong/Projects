#!/usr/local/bin/bash

# Tool: Reset Commit History
# Author: Timothy Tong
# Description: Resets commit history in all user repos. Applies helper function (G, see heredoc) that lists all user repo links.
# Usage: Define the helper function somewhere and run the script.

# The G helper prints out links for all of the user's repositories. It can be defined in .bashrc
<<'END_COMMENT'
export PAT=<USER'S PAT TOKEN>                           # Github personal access token for authentication 
G () {
    curl -L \                                           # Use Github's REST API endpoint get repository info
        -H "Accept: application/vnd.github+json" \
        -H "Authorization: Bearer $PAT" \
        -H "X-GitHub-Api-Version: 2022-11-28" \
        https://api.github.com/user/repos |\
    awk '/^    "html_url"/' |\                          # Process and select just the relevant, repository urls
    cut -d\" -f 4
}
END_COMMENT

# Need to source .bashrc here if defined helper there to use it
. ~/.bashrc 

# Creates dummy folder to clone repos into (let user manually delete)
cd ~/Desktop
mkdir dummy_folder
cd dummy_folder

# Pipe output of helper to read each line in while loop
G | while read URL
do
    git clone $URL                           # Clones each repo and changes dir inside
    cd $(echo $URL | cut -d/ -f5)
    git checkout --orphan fresh_start        # Creates an Orphan Branch (no commit history)
    git add -A                               # Adds all files in the working directory to the staging area. 
    git commit -am "Added file and cleanup"  # Commits the staged changes to the orphan branch
    git branch -D main                       # Delete previous main branch
    git branch -m main                       # Rename current branch to main
    git push -f origin main                  # Force push new main branch to remote repo, replacing history
    cd ..                                    # Change back to original directory
done
