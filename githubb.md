1. One-Time Setup (If you haven't done this yet)Before you start, tell Git who you are.
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"

2. Start a RepositoryNavigate to your project folder and initialize Git.
Bash
cd my-project-folder
git init
git init: Turns the current directory into a Git repository.

3. Save Changes (The "Save" Loop)This is the cycle you will repeat often.
Check status (See what has changed):
git status
Stage files (Prepare them to be saved):
git add .
(The . adds all changed files. To add a specific file, use git add filename.py)

Commit (Actually save the snapshot):
git commit -m "Description of changes"

4. Connect to Remote (GitHub/GitLab)To push code, your local computer needs to know where to send it.

Option A: Standard Git (Requires creating repo on website first)Go to GitHub, create a "New Repository", and copy the URL (ending in .git).
Run this in your terminal:
git remote add origin https://github.com/YourUsername/RepoName.git
git branch -M main
Option B: The "No Website" Way (Requires GitHub CLI)If you have gh installed, you can create the remote repo entirely from the terminal:
gh repo create my-project-name --public --source=. --remote=origin

5. Push and Pull (Syncing)First time pushing:You need to set the "upstream" link so Git remembers where to push.
git push -u origin main
After the first time:Upload changes:
git push
Download changes (if you edited code on another PC):
git pull


Action,          Command
Start,           git init
Stage All,       git add .
Commit,          "git commit -m ""msg"""
Push,            git push
Pull,            git pull
Check Status,    git status
View History,    git log --oneline