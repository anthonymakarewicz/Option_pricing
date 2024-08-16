# Option Pricer

## Repository Assumptions and Guidelines

This repository follows a structured workflow to ensure code quality, stability, and consistency.
Below are the key assumptions and guidelines that contributors should follow:

### Branching Strategy

1. **Main Branch (`main`)**:
    - The `main` branch contains stable, production-ready code.
    - Direct pushes to the `main` branch are **not allowed**. All changes must be introduced via pull requests (PRs).
    - Before merging into `main`, all PRs must pass the CI/CD pipeline and receive necessary approvals.


2. **Development Branch (`dev`)**:
    - The `dev` branch is the primary branch for ongoing development.
    - All feature branches should be created from `dev`.
    - In order to update changes from feature branches to the `dev` branch, you must create a PR that will also trigger
   the CI/CD pipeline to ensure that ongoing development does not introduce errors.


3. **Feature Branches (`feature/*`)**:
    - Feature branches are used for developing new features and should be created from `dev`.
    - Once a feature is complete and tested,  you must create a PR to merge it back into `dev`.
    - Example: `feature/your-feature-name`.


4. **Release Branches (`release/*`)**:
    - Release branches are created from `dev` when preparing for a new production release.
    - After final testing and necessary changes, release branches are merged into both `main` and `dev`.
    - Example: `release/1.0`.


5. **Hotfix Branches (`hotfix/*`)**:
    - Hotfix branches are created from `main` to address critical issues found in production.
    - After fixing the issue, hotfix branches are merged into both `main` and `dev`.
    - Example: `hotfix/issue-name`.

### CI/CD Pipeline

1. **Continuous Integration/Continuous Deployment (CI/CD)**:
    - The CI/CD pipeline is triggered by pushes to any branch except `main` and `dev`
      for which you should create a Pull Request.
    - The pipeline includes steps such as building the project, running tests, and static code analysis (e.g., using `clang-tidy`).


2. **Pull Requests and CI/CD**:
    - To merge changes into `main` and `dev`, you must create a pull request (PR).
    - The CI/CD pipeline automatically runs for each PR to validate the changes.
    - Only after the CI/CD pipeline passes and the PR is approved can it be merged into `main` or `dev`.

### Workflow Guidelines

1. **Creating a Feature Branch**:
   - Ensure you're on the `dev` branch:
     ```sh
     git checkout dev
     git pull origin dev
     git checkout -b feature/your-feature-name
     ```

2. **Committing Changes**:
   - Add and commit your changes with descriptive messages:
     ```sh
     git add .
     git commit -m "Add new feature"
     ```

3. **Pushing Changes**:
   - Push the feature branch to the remote repository to trigger the CI/CD pipeline:
     ```sh
     git push -u origin feature/your-feature-name
     ```

4. **Creating a Pull Request**:
   - Navigate to the repository on GitHub.
   - Click on the "Pull requests" tab and "New pull request".
   - Select `main` as the base branch and your feature branch as the compare branch.
   - Fill in the title and description and click "Create pull request".


5. **Merging a Pull Request**:
   - Ensure all CI/CD checks pass and the PR is approved.
   - Merge the PR on GitHub to integrate changes into `main`.
   - Pull changes from origin/main to local main by calling `git pull` inside main.

## General Guidelines

### Regularly Merging Changes from `dev` to Your Feature Branch

1. **Fetch Latest Changes**:
   - Fetch the latest changes from the remote `dev` branch:
     ```sh
     git fetch origin
     ```

2. **Update Local `dev` Branch**:
   - Ensure your local `dev` branch is up-to-date:
     ```sh
     git checkout dev
     git pull origin dev
     ```

3. **Merge `dev` into Your Feature Branch**:
   - Switch back to your feature branch and merge the updated `dev` branch:
     ```sh
     git checkout feature/your-feature-name
     git merge dev
     ```

4. **Resolve Conflicts**:
   - If there are conflicts, resolve them manually in the conflicted files.


5. **Commit the Merge**:
   - After resolving conflicts, commit the merge:
     ```sh
     git add .
     git commit -m "Merge dev into feature/your-feature-name"
     ```

### Handling Merge Conflicts

1. **Identify Conflicts**:
   - Check the conflicting files:
     ```sh
     git status
     ```

2. **Resolve Conflicts**:
   - Open the conflicted files and manually resolve the conflicts by choosing which changes to keep or combining them.


3. **Mark as Resolved**:
   - Add the resolved files to the staging area:
     ```sh
     git add <resolved-file>
     ```

4. **Commit the Resolution**:
   - Commit the resolved conflicts:
     ```sh
     git commit -m "Resolve merge conflict in <file>"
     ```

## Example workflows

### Feature Development Workflow for `dev` Branch

1. **Switch to `dev` and pull latest changes to avoid conflicts**:
```sh
git checkout dev 
git pull origin dev
```
2. **Create a feature branch from `dev`**:
```sh
git checkout -b feature/your-feature dev
```
3. **Make changes, add and commit**:
```sh
git add .
git commit -m "Add new feature"
```
4. **Push the feature branch to remote to trigger the CI/CD pipeline**:
```sh
git push -u origin feature/your-feature
```

5. **Regularly update your feature branch with changes from `dev`**:
```sh
git fetch origin
git checkout dev
git pull origin dev
git checkout feature/your-feature
git merge dev
```
6. **Create a pull request (PR) to merge the feature branch into dev**:
- Navigate to the repository on GitHub.
- Click on the "Pull requests" tab and "New pull request".
- Select dev as the base branch and your feature branch as the compare branch.
- Fill in the title and description and click "Create pull request".
7. **Ensure all CI/CD checks pass and the PR is approved**:
 - Monitor the CI/CD pipeline and address any issues.
 - Once the PR is approved, merge it on GitHub.

8. **Pull the latest changes from dev to your local repository**:
```sh
git checkout dev
git pull origin dev
```

9. **Delete the feature branch on local and on remote**:
```sh
git branch -d feature/your-feature
git push origin --delete feature/your-feature
```

## Contact
For any questions and/or contributions,
please contact Anthony Makarewicz at anthonymakarewicz@gmail.com