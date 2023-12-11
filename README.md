# Mini Project - 5: Digital Filters
## 411086030 劉家瑋
###### >  第四次作業
* 繪製的 impulse responses
![image](https://github.com/0615liu/mini-project-5/assets/149355132/4637454f-c3a8-429b-9e83-2f0ae6dcf403) (圖一)
> 圖一左聲道 M=8時 會有2*8+1=17點 (txt會有17筆數)  

![image](https://github.com/0615liu/mini-project-5/assets/149355132/7176a51f-f175-4a81-a169-d80d2a4ed968) (圖二)
> 圖二右聲道 M=8時 會有2*8+1=17點 (txt會有17筆數)

![image](https://github.com/0615liu/mini-project-5/assets/149355132/5e317ab3-5e73-4877-9208-26297a429651) (圖三)
> 圖三左聲道 M=32 會有2*32+1=65點 (txt會有65筆數)
>> 這邊會發現像sinc函數，當sinc傅立葉時變方波

![image](https://github.com/0615liu/mini-project-5/assets/149355132/ee1af71f-d4cd-40d1-a7c4-750136398b69) (圖四)
> 圖四右聲道 M=32 會有2*32+1=65點 (txt會有65筆數)

![image](https://github.com/0615liu/mini-project-5/assets/149355132/5c18e9bc-fd22-40a9-ab46-8c0900b8bd48) (圖五)
> 圖五左聲道 M=1024 會有2*1024+1=2049點 (txt會有2049筆數)

![image](https://github.com/0615liu/mini-project-5/assets/149355132/32e7a396-04e8-4f5e-8961-2bd15e453fa5) (圖六)
> (圖六)右聲道 M=1024 會有2*1024+1=2049點 (txt會有2049筆數)

### 我們的response 有幾個點，取決M，2M+1也能看出response是對稱的

* 繪製的 log spectrum
![image](https://github.com/0615liu/mini-project-5/assets/149355132/92c55e13-4041-403e-b0a5-34b36912ccfc) (圖七)
> (圖七)左聲道頻譜 M=8
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/3b0cb116-c168-4352-b0f7-28d78f47cb40) (圖八)
> (圖八)左聲道頻譜 M=32
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/1febd5b3-5f8f-4c45-a29d-97941603d441) (圖九)
> (圖九)左聲道頻譜 M=1024
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/671344d1-46dc-4649-b16d-136aa915b97d) (圖十)
> (圖十)右聲道頻譜 M=8
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/74c90d99-7a92-4bfd-bc57-4312ba55e4f0) (圖十一)
> (圖十一)右聲道頻譜 M=32
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/77431f31-24a8-4b27-8346-29ed06cdd247) (圖十二)
> (圖十二)右聲道頻譜 M=1024
## 頻譜如何產生?
> y<sub>L</sub>[n]= h<sub>L</sub> [n] * x<sub>L</sub>[n]  透過DFT變換得到頻域 (時域convolution，頻域相乘)
>> h<sub>L</sub>[n] 有2M+1個點，代表會拿2M+1點去convolution，M越大越精確
>> 
### M影響結果 (從頻譜觀察)
> 從audicity來看頻譜(bandpass和bandstop)，以M=8和1024比較
* 關於M的影響
> 當M越大，則會切割越乾淨，反之。所以當M為1024時，會比M為32的濾波效果更好 (audicity)
> ![image](https://github.com/0615liu/mini-project-5/assets/149355132/6397efc3-6957-41b9-ab45-91b688fbcfdf)
>>此圖為原始blue_giant_fragment.wav 下方會透過濾波器，看出M越大 效果越佳
>
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/37a43ece-3e31-47b0-8dce-d709ea03783b)   
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/4b78a284-493d-4c13-9446-07653dc0ae0e)   
>
> 上圖為M=8，下圖M=1024，然而兩張圖上半部為左聲道(bandpass)，下部分為右聲道(bandstop)
>
### 從時域觀察
![image](https://github.com/0615liu/mini-project-5/assets/149355132/92b1af8b-633c-462f-800c-6350ae4429e6)
> blue_giant_fagment 時域圖
>
![image](https://github.com/0615liu/mini-project-5/assets/149355132/8811beb2-0da0-47f2-9466-dafa26fc35ae)
> M=8 時域圖
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/b337edbc-3214-4ef5-90c9-d488801760f1)
> M=32 時域圖
> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/5dcdb424-39f1-4a4b-b9ed-f1761dbe1899)
 > M=1024 時域圖
>
* 會發現不論在左右聲道都被改變訊號(經convolution)，但不容易看出來是如何被濾除訊號，所以還是以頻譜來觀察為佳
>
#### 本次作業要求兩種濾波器在1500至3500赫茲會有邊界
>> 代表bandpass在1500到3500赫茲，理想上有值
>> 代表bandstop在1500到3500赫茲，理想上無值

###  log spectrum 顯示的濾波結果是否正確？如何證明？
> 首先, 20.060 秒到 20.085 秒之間的 1200 個點
>> 因為(20.085-20.060)*48000=1200
> 如何從頻譜看是左聲道輸出還是右聲道輸出?
>> 我們發現頻譜在1500到3500赫茲有較多成分(0至1500 & 超過3500赫茲 較低成分)，那會是bandpass，也就是左聲道
>> 若在0到1500赫茲以及3500以上赫茲有較高成分，理論上會是bandstop，但我們在右聲道圖發現0到1500赫茲確實符合，到3500赫茲以上我認為是音檔本身在頻譜成分就低，雖然經過頻譜響應，但仍然不大

### bandpass如何轉bandstop(右聲道)

> 透過通訊原理正課所教的bandpass

>![image](https://github.com/0615liu/mini-project-5/assets/149355132/64c928cb-69cf-410c-bc77-540e71c911d8)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/976d2025-5f70-4b6d-9a0f-aa86bed027cd)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/460a080d-5d17-4a31-a47e-f658b9293daa)
>>
> 
>
>而bandstop與bandpass頻譜互補為1
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/79c34af7-b16a-4b3d-93a8-b4c163c62212)
>>
> 為bandstop

```js
   float BANDSTOP(int m, int n) // bandstop and bandpass in freq domain sigma will be 1
   {
    float wh = 2 * PI * FH / FS;
    float wl = 2 * PI * FL / FS; 
    if (n == m) // n=0
    {
        return 1.0- (wh / PI - wl / PI); // inverse fourier transform if 1 is delta
    }
    else // n unequal to 0
    {
        return -(sinf(wh * ((float)(n - m))) - sinf(wl * ((float)(n - m)))) / PI / ((float)(n - m)) * hamming(2 * m + 1, n);
    }
  }
```

# 程式補充
> 利用 spectrogram 觀察訊號的頻率成份,所以可以用上一次程式的DFT



