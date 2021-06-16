git filter-branch --commit-filter '
        if [ "$GIT_AUTHOR_EMAIL" != "66552663+faceslog@users.noreply.github.com" ];
        then
                GIT_AUTHOR_NAME="faceslog";
                GIT_AUTHOR_EMAIL="66552663+faceslog@users.noreply.github.com";
                git commit-tree "$@";
        else
                git commit-tree "$@";
        fi' HEAD
