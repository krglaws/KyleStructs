
ERRTITLE="TESTS FAILED:"
FAILED=""

TESTBIN="tests/bin"

for TESTFILE in $(ls $TESTBIN)
do
	./$TESTBIN/$TESTFILE
	if [ $? != 0 ]
	then
		FAILED="${FAILED}${TESTFILE}\n"
	fi
done
	

if [ "$FAILED" != "" ]
then
	echo $ERRTITLE
	echo $FAILED
	ERR=1	
fi

ERR=0


