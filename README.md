# 構造体の中身

## メイン構造体
- 開始時間(starttime)
- 終了フラグ(stoped)
- 渡されたパラメタたち  
	- 哲学者の数(num_of_philo)  
	- 死ぬまでの時間(time_to_die)  
	- 食べるまでの時間(time_to_eat)  
	- 睡眠時間(time_to_sleep)  
	- 食事回数上限(num_of_eat_time)  
	- 食事回数上限が設定されているかどうか(specified_eat_time)
- フォークのぶんの mutex リスト(forks)
- printf 用 mutex(mutex_print)
- データ参照制御用の mutex(mutex_data)  

## 各哲学者データ  
- 哲学者id(id)  
- 右側フォークの idx(right_fork)  
- 左側フォークの idx(left_fork)  
- 最後に食事した時刻(lastmeal_time)  
- 食事回数(num_of_meals)  
- 哲学者スレッド(thread)  
- メイン構造体(d)
 

---

# メイン関数

- [x] 入力エラーチェック  
- [x] 構造体を初期化  
- [X] フォークの数だけ `pthread_mutex_init`  
- [x] printf 用の `pthread_mutex_init`  
- [x] データ参照用の `pthread_mutex_init`  
- [x] 哲学者の数だけ `pthread_create`  
- [x] 監視スレッドを `pthread_create`  
- [x] 哲学者の数だけ `pthread_join`  
- [x] 監視スレッドを `pthread_join`  
- [x] フォークの数だけ `pthread_mutex_destroy`  
- [x] printf 用の `pthread_mutex_destroy`  
- [x] 哲学者データ参照用の `pthread_mutex_destroy`

---

# 哲学者ごとのスレッドの中

- [x] 哲学者が一人だけの場合、フォークを持ってtime_to_die待機
- ループ  
	- [x] 終了フラグが立っていたら return する  
	- [x] 奇数は右→左、偶数は左→右 と順序を変えてフォークを確保  
	- [x] フォークの待機リストに自身のidを追加し、自身のidがリストの先頭になったらmutex確保
		- [x] `timestamp_in_ms X has taken a fork` を出力 ※1 2 3  
		- [x] `timestamp_in_ms X is eating` を出力 ※1 2 3  
			- [x] 食事時間分待機  
			- [x] 食事回数追加  
			- [x] フォーク確保を解除  
			- [x] 食事回数上限を超えていたら break する  
		- [x] `timestamp_in_ms X is sleeping` を出力 ※1 2 3  
			- 睡眠時間分待機  
		- [x] `timestamp_in_ms X is thinking` を出力 ※1 2 3  
- ※1 printf 用 mutex を見て出力する  
- ※2 データ参照・更新前は mutex を見る  
- ※3 毎回終了フラグを見て立っていたら出力しない  

---

# 監視スレッドの中

- 各哲学者が全員処理終了になるまでループ  
	- [x] 哲学者ループ  
		- [x] 最後に食事した時間 > time_to_die 超過の場合  
			- [x] `timestamp_in_ms X died` を出力 ※1 2  
			- [x] 終了フラグを立てて処理を抜ける
		- [x] 全員が規定回数食事が終わっていた場合、処理を抜ける

