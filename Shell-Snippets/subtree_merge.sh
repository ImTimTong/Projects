#!/usr/local/bin/bash

# Tool: Subtree Merge
# Author: Timothy Tong
# Description: Adds all user repos as subtrees in a new main "Projects" repo.
# Usage: Add G helper function to .bashrc (see reset_commit_history.sh). Run script anywhere.

# Source .bashrc for helper function
. ~/.bashrc

# Navigate to the Desktop and create a Projects directory
cd ~/Desktop/
mkdir Projects
cd Projects

# Setup main repository
echo "# Projects" >> README.md                                              # Create README
git init                                                                    # Initialize repo
git add README.md                                                           # Stage README
git commit -m "Initial commit"                                              # Commit changes
git branch -M main                                                          # Rename branch to main
git remote add origin https://github.com/ImTimTong/Projects.git             # Add remote to my repo (replace with own user)
git push -u origin main                                                     # Push changes and set upstream


# Add each user repo as a subtree
G | grep -v "Projects" | while read URL                                     # Pipe output of G except "Projects" url
do
    name=$(echo $URL | cut -d/ -f5)                                         # Extract repo name
    git remote add -f $name $URL                                            # Add remote for target repo
    git merge -s ours --no-commit --allow-unrelated-histories ${name}/main  # Merge into main repo the target repo, keeping only main content
    git read-tree --prefix=${name}/ -u ${name}/main                         # Copy target repo history to new subfolder
    git commit -m "Subtree merged in $name"                                 # Commit changes                                        
done

# Push all changes to remote repo
git push
