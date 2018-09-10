char* convert(char* s, int numRows) {
    int i,j,k,length,gap;
    i=j=k=0;
    length=strlen(s);
    gap=2*numRows-2;
    char *res;
    res=(char*)malloc((length+1)*sizeof(char));
    if(numRows==1) 
        return s;
    for(i=0;i<numRows;i++) {
        for(j=0;j+i<length;j=j+gap) {
            res[k++]=s[i+j];
            if(i != 0 && i!= numRows-1 && j+gap-i<length)
                res[k++]=s[j+gap-i];
        }
    }
    res[k]='\0';
    return res;
}