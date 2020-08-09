# 課題4 レポート

bb35319025 新開　大生

## 課題

[../sample/heights.csv]は標本全体（男性と女性合わせた14人）のデータをまとめたものである．
一方，[../sample/IDs.csv]は標本14人の学籍番号（身長データと同じ順番）である．
学籍番号を尋ねて，その学籍番号のデータがリストにあれば，学籍番号，身長，性別のデータを表示し，リストになければ，「No data」と表示せよ．

この二つのファイルを読み取り，学籍番号，身長，性別の3つをメンバーとする構造体の配列で管理するとよい．

## ソースコードの説明

    6～10行目　性別、身長、IDを構造体としてDataと定義する
    22～31行目　指名したストリームをオープンして、情報をFILE構造体に格納しそのポインタを返し、NULLならエラーを返す
    33～43行目　定義した構造体の項目genderとheightにデータを入力し、EOFならエラーを返す
    46～53行目　22～31行と同様に、IDのファイルを読み込む
    56～63行目　iを初期化し、33～43行目と同様に、項目IDにデータを入力する
    66，67行目　指定したIDをsheck_IDに格納する
    69～86行目　指定したIDが構造体に存在するならば、if文でi番目のgenderが1なら男性、そうでないなら女性と判断し、i番目のheightのデータを返す。IDが構造体の中になければ"No data"と返す

## 入出力結果

例えば，ID 45313125のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313125
---
ID : 45313125
gender : Female
height : 152.4
```

例えば，ID 45313124のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313124
---
No data
```

## 修正履歴
[comment #20200722]
- おそらく, IDに関するファイルを fopen していないにもかかわらず fclose しているため file close error になっています. 

[comment #20200730]
- l.74 の条件文がおかしいです. genderに入っているのは 1か2 のはずです. 

[comment #20200731]
- OKです. 

[comment #20200804 sonoda]
- これのif文の処理がキモいです．
  ```
  while(fgets(buf,sizeof(buf),fp) !=NULL){
        if(i== -1){
            i++;
            continue;
        }
        sscanf(buf,"%d,%lf",&data[i].gender,&data[i].height);
        i++;
    }
  ```
  `i= -1;`で初期化していて，1回目のループ（i == -1)のときはsscanfを動かさないで次のループに行く，ということで1行読み飛ばすということなのだと思います．
  しかし，パッと見では，何をしたいのかわからず，帳尻合わせにしか見えません．
  
  i=0;で初期化し，このif文を消し，その代わりに，while文の直前に，
  ```
  fgets(buf,sizeof(buf),fp);
  ```
  を挿入するのがよいのではないかと思います．
  
