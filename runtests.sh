
ERRTITLE="TESTS FAILED:"
FAILED=""

TESTBIN="tests/bin"

echo ==============================
echo ----------------------------
echo Running all test suites...

for TESTFILE in $(ls $TESTBIN)
do
	./$TESTBIN/$TESTFILE
	if [ $? != 0 ]
	then
		FAILED="${FAILED}${TESTFILE}\n"
	fi
done

echo Done.
echo ----------------------------
echo ==============================
	

if [ "$FAILED" != "" ]
then
	echo $ERRTITLE
	echo $FAILED
	exit 1
fi

exit 0 


