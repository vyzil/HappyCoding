// a,b,d[5];m(f,x,y){return f&&x>y?y:x;}main(i){for(;scanf("%d",&a),a;d[b=a]=0)for(i=!b?*d=2:0;i<5;i++)if(d[i]){if(a-b)d[b]=m(i,d[i]+(i?a-i?(a-i)%2?3:4:1:2),d[b]);if(i-a&&i-b)d[i]+=b?b-a?(b-a)%2?3:4:1:2;}for(i=5;--i;)*d=m(d[i],*d,d[i]);printf("%d",*d);}


a,b,d[5];
m(f,x,y) { 
    return f && x > y ? y : x ;
}

main(i) {
    for( ; scanf("%d",&a), a; d[b=a]=0)
        for(i = !b ? *d=2 : 0; i<5 ; i++)
            if(d[i]) {
                if(a-b) d[b] = m(i, d[i] + (i ? a-i? (a-i) % 2 ? 3 : 4 : 1 : 2), d[b]);
                if(i-a && i-b) d[i] += b ? b-a ? (b-a) % 2 ? 3:4:1:2;
            }

    for(i=5; --i; ) *d = m(d[i], *d, d[i]);
    printf("%d",*d);
}