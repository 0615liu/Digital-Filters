# Mini Project - 5: Digital Filters
## 411086030 通訊三 劉家瑋
###### >  第四次作業
* 繪製的 impulse responses
![image](https://github.com/0615liu/mini-project-5/assets/149355132/4637454f-c3a8-429b-9e83-2f0ae6dcf403)
> 左聲道 M=8時 會有2*8+1=17點
>> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/5e317ab3-5e73-4877-9208-26297a429651)
> 左聲道 M=32 會有2*32+1=65點
>> 
![image](https://github.com/0615liu/mini-project-5/assets/149355132/5c18e9bc-fd22-40a9-ab46-8c0900b8bd48)
> 左聲道 M=1024 會有2*1024+1=2049點
  
![image](https://github.com/0615liu/mini-project-5/assets/149355132/7176a51f-f175-4a81-a169-d80d2a4ed968)
> 右聲道 M=8時 會有2*8+1=17點

![image](https://github.com/0615liu/mini-project-5/assets/149355132/4a1fa8f0-4214-488c-9700-1479de55b078)
> 右聲道 M=32 會有2*32+1=65點

![image](https://github.com/0615liu/mini-project-5/assets/149355132/32e7a396-04e8-4f5e-8961-2bd15e453fa5)
> 右聲道 M=1024 會有2*1024+1=2049點

### 我們的response 有幾個點，取決M，2M+1也能看出response是對稱的

* 繪製的 log spectrum
![image](https://github.com/0615liu/mini-project-5/assets/149355132/92c55e13-4041-403e-b0a5-34b36912ccfc)
> 左聲道頻譜 M=8
![image](https://github.com/0615liu/mini-project-5/assets/149355132/3b0cb116-c168-4352-b0f7-28d78f47cb40)
> 左聲道頻譜 M=32
![image](https://github.com/0615liu/mini-project-5/assets/149355132/1febd5b3-5f8f-4c45-a29d-97941603d441)
> 左聲道頻譜 M=1024
![image](https://github.com/0615liu/mini-project-5/assets/149355132/671344d1-46dc-4649-b16d-136aa915b97d)
> 右聲道頻譜 M=8
![image](https://github.com/0615liu/mini-project-5/assets/149355132/2a74390b-f104-41cd-bff7-f1b1896df68c)
> 右聲道頻譜 M=32
![image](https://github.com/0615liu/mini-project-5/assets/149355132/77431f31-24a8-4b27-8346-29ed06cdd247)
> 右聲道頻譜 M=1024
## 頻譜如何產生?
> y<sub>L</sub>[n]= h<sub>L</sub> [n] * x<sub>L</sub>[n]  透過DFT變換得到頻域 (時域convolution，頻域相乘)
>> h<sub>L</sub>[n] 有2M+1個點
### M影響結果
> 從audicity來看頻譜(bandpass和bandstop)，以M=8和1024比較
* 關於M的影響
> 當M越大，則會切割越乾淨，反之。所以當M為1024時，會比M為32的濾波效果更好 (audicity)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/37a43ece-3e31-47b0-8dce-d709ea03783b)   
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/4b78a284-493d-4c13-9446-07653dc0ae0e)   
>
> 上圖為M=8，下圖M=1024，然而兩張圖上半部為左聲道(bandpass)，下部分為右聲道(bandstop)
#### 本次作業要求兩種濾波器在1500至3500赫茲會有邊界
>> 代表bandpass在1500到3500赫茲，理想上有值
>> 代表bandstop在1500到3500赫茲，理想上無值

###  log spectrum 顯示的濾波結果是否正確？如何證明？
> 首先, 20.060 秒到 20.085 秒之間的 1200 個點
>> 因為(20.085-20.060)*48000=1200
> 為何頻域只有24000
>> 因為48000/2=24000，也就是+-24000，我們只記錄正頻率

### bandpass如何轉bandstop(右聲道)

> 透過通訊原理正課所教的bandpass




>![image](https://github.com/0615liu/mini-project-5/assets/149355132/64c928cb-69cf-410c-bc77-540e71c911d8)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/976d2025-5f70-4b6d-9a0f-aa86bed027cd)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/460a080d-5d17-4a31-a47e-f658b9293daa)
>
>而bandstop與bandpass頻譜互補為1
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/79c34af7-b16a-4b3d-93a8-b4c163c62212) (圖一)
>
>> 圖一為bandstop

```js
    float band_stop(int m, int n)  //time domain
    {
      float wh = 2*PI*FH/FS;
      float wl = 2*PI*FL/FS;
      if(n==m) //when n come to 0
      {
		    return 1.0-1.0*(wh/PI - wl/PI);
	    }
	    else 
      {
		    return -1.0*(sinf(wh*((float)(n-m)))-sinf(wl*((float)(n-m))))/PI/((float)(n-m)) * hamming(2*m+1, n);
      }
   }
```





