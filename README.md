構造体の中身
・開始時間
・パラメタとして渡された
       哲学者の数
       死ぬまでの時間
       ⾷べるまでの時間
       睡眠時間
       食事回数上限
　　食事回数上限が設定されているかどうか

・フォークのぶんのmutexリスト
・printf用mutex
・各哲学者データ
        id
        右側フォークのidx
        左側フォークのidx
        最後に食事した時刻
        食事回数
　　哲学者スレッド
        データ参照用のmutex
        data

メイン関数
　・エラーチェック
    ・構造体を初期化
　・フォークの数だけpthread_mutex_init
    ・printf用のpthread_mutex_init
    ・データ参照用のpthread_mutex_init
　・哲学者の数だけpthread_create
    ・監視スレッドをpthread_create
　・哲学者の数だけpthread_join
    ・監視スレッドをpthread_join
　・フォークの数だけpthread_mutex_destroy
    ・printf用のpthread_mutex_destroy
    ・哲学者データ参照用のpthread_mutex_destroy

哲学者ごとのスレッドの中
    ・哲学者が一人だけの場合、フォークを持って一定時間経過後死亡
    ・ループ
    　終了フラグが立っていたらreturnする
        　奇数は右→左、偶数は左→右 と順序を変えてフォークを確保
            「timestamp_in_ms X has taken a fork」を出力※1 2 3
            「timestamp_in_ms X is eating」を出力※1 2 3
                食事時間分待機
                食事回数追加
                フォーク確保を解除
                食事回数上限を超えていたらreturnする
            「timestamp_in_ms X is sleeping」を出力※1 2 3
                睡眠時間分待機
            「timestamp_in_ms X is thinking」を出力※1 2 3
        ※1 printf用mutexを見て出力する
        ※2 データ参照・更新前はmutexを見る
        ※3 毎回終了フラグを見て立っていたら出力しない

監視スレッドの中
　・各哲学者が全員処理終了になるまでループ
　　哲学者分ループ
            最後に食事した時間 　>　time_to_die 超過の場合
                「timestamp_in_ms X died」を出力※1 2
                終了フラグを立てて処理を抜ける
