#!make -f
git:
	git add --all
	git commit -m "$m"
	git push