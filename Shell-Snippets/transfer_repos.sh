#!/usr/local/bin/bash

# Tool: Transfers all repos to another user
# Author: Timothy Tong
# Usage: Applies helper function G to get all repo links. Accesses Github REST API endpoint for repository transfer.

. ~/.bashrc

G | while read URL
do
    user_and_repo=$(echo $URL | cut -d/ -f4-5)                  # Extract "name/repo"
    curl -L \
      -X POST \
      -H "Accept: application/vnd.github+json" \
      -H "Authorization: Bearer $PAT" \
      -H "X-GitHub-Api-Version: 2022-11-28" \
      https://api.github.com/repos/${user_and_repo}/transfer \
      -d '{"new_owner":"<INSERT NEW USER>"}'                    # Enter user want to transfer to
done
