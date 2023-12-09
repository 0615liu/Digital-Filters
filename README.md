# Mini Project - 5: Digital Filters
* 出發點
>  第四次作業
>>bandpass如何轉bandstop(右聲道)
>>透過通訊原理正課所教的bandpass
>>
>![image](https://github.com/0615liu/mini-project-5/assets/149355132/64c928cb-69cf-410c-bc77-540e71c911d8)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/976d2025-5f70-4b6d-9a0f-aa86bed027cd)
>>![image](https://github.com/0615liu/mini-project-5/assets/149355132/460a080d-5d17-4a31-a47e-f658b9293daa)
>
>而bandstop與bandpass頻譜互補為1
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

* 關於M的影響
> 當M越大，則會切割越乾淨，反之。所以當M為1024時，會比M為32的濾波效果更好
