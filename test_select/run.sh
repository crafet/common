
## 客户端模拟每1s发起一次连接


function run()
{
	BIN=./client/client
	while [ 1 ];
	do
		PORT=$((7777 + $RANDOM%1000))
		
		$BIN $PORT || exit 1
		sleep 2s
	done
	return 0
}


## main

run "" || exit 1

