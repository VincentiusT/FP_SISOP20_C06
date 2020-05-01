    #include "types.h"
    #include "stat.h"
    #include "user.h"
    #include "fcntl.h"
    #include "fs.h"

    unsigned char encoding_table[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                    'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                    '4', '5', '6', '7', '8', '9', '+', '/'};



    unsigned char check(char isi){
        if (isi >= 65 && isi <= 90) //Between A-Z
            isi -= 65;
        else if (isi >= 97 && isi <= 122)
            isi -= 97 + 26;
        else if (isi >= 48 && isi <= 57) //Between 0-9
            isi = isi - 48 + 52;
        else if (isi == 43) // +
            isi = 62;
        else if (isi == 47) // /
            isi = 63;
        return(isi);
    }

    int base64_encode(unsigned char in[], unsigned char out[], int count, int newline_flag, int tanda){
    int index,index2,sum,left_over;

    sum = (count / 3) * 3;
    for (index=0,index2=0; index < sum; index += 3,index2 += 4) {
            out[index2] = encoding_table[in[index] >> 2];
            out[index2+1] = encoding_table[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
            out[index2+2] = encoding_table[((in[index+1] & 0x0f) << 2) + (in[index+2] >> 6)];
            out[index2+3] = encoding_table[in[index+2] & 0x3F];
            
            if (!(index2 % (tanda+1)) && newline_flag) {
                out[index2+4] = '\n';
                index2++;
            }
    }
    left_over = count % 3;
    if (left_over == 1) {
        out[index2] = encoding_table[in[index] >> 2];
        out[index2+1] = encoding_table[(in[index] & 0x03) << 4];
        out[index2+2] = '=';
        out[index2+3] = '=';
        index2 += 4;
    }
    else if (left_over == 2) {
        out[index2] = encoding_table[in[index] >> 2];
        out[index2+1] = encoding_table[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
        out[index2+2] = encoding_table[(in[index+1] & 0x0F) << 2];
        out[index2+3] = '=';
        index2 += 4;
    }
    out[index2] = '\0';
    return(index2);
    }


    int base64_decode(unsigned char in[], unsigned char out[], int count, int newline_flag, int tanda)
    {
        int index,index2,sum,left_over;

        if (in[count-1] == '=')
            count--;
        if (in[count-1] == '=')
            count--;

        sum = (count / 4) * 4;
        for (index=0,index2=0; index2 < sum; index += 3,index2 += 4) {
            out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
            out[index+1] = (check(in[index2+1]) << 4) + (check(in[index2+2]) >> 2);
            out[index+2] = (check(in[index2+2]) << 6) + check(in[index2+3]);

            if (!(index2 % (tanda+1)) && newline_flag) {
                out[index2+4] = '\n';
                index2++;
            }    int index,index2,sum,left_over;

            if (in[count-1] == '=')
                count--;
            if (in[count-1] == '=')
                count--;

            sum = (count / 4) * 4;
            for (index=0,index2=0; index2 < sum; index += 3,index2 += 4) {
                out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
                out[index+1] = (check(in[index2+1]) << 4) + (check(in[index2+2]) >> 2);
                out[index+2] = (check(in[index2+2]) << 6) + check(in[index2+3]);

                if (!(index2 % (tanda+1)) && newline_flag) {
                    out[index2+4] = '\n';
                    index2++;
                }
            }
            left_over = count % 4;
            if (left_over == 2) {
                out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
                out[index+1] = (check(in[index2+1]) << 4);
                index += 2;
            }
            else if (left_over == 3) {
                out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
                out[index+1] = (check(in[index2+1]) << 4) + (check(in[index2+2]) >> 2);
                out[index+2] = check(in[index2+2]) << 6;
                index += 3;
            }
            out[index] = '\0';
            return(index);
        }
        left_over = count % 4;
        if (left_over == 2) {
            out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
            out[index+1] = (check(in[index2+1]) << 4);
            index += 2;
        }
        else if (left_over == 3) {
            out[index] = (check(in[index2]) << 2) + ((check(in[index2+1]) & 0x30) >> 4);
            out[index+1] = (check(in[index2+1]) << 4) + (check(in[index2+2]) >> 2);
            out[index+2] = check(in[index2+2]) << 6;
            index += 3;
        }
        out[index] = '\0';
        return(index);
    }

    int main(int argc, char *argv[]){
        if(argc==2){
            int inputfile;
            if((inputfile = open(argv[1],O_RDONLY)) < 0){
                close(inputfile);
                exit();
            }
            int count_buff;
            unsigned char output[1024],data[1024];
            while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
            base64_encode(data, output, strlen((char*)data),0,76);
            printf(1,"%s\n",output);
            close(inputfile);
            exit();
    }
    else if(argc==3){
            if((strcmp(argv[1],"-d"))==0){
                int inputfile;
                if((inputfile = open(argv[2],O_RDONLY)) < 0){
                close(inputfile);
                exit();
                }
                int count_buff;
                unsigned char output[1024],data[1024];
                while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
                base64_decode(data, output, strlen((char*)data),0,76);
                printf(1,"%s\n",output);
                close(inputfile);
                exit();
            }
            else if((strcmp(argv[1],"-e"))==0){
                int inputfile;
                if((inputfile = open(argv[2],O_RDONLY)) < 0){
                close(inputfile);
                exit();
                }
                int count_buff;
                unsigned char output[1024],data[1024];
                while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
                base64_encode(data, output, strlen((char*)data),0,76);
                printf(1,"%s\n",output);
                close(inputfile);
                exit();  
            }
    }
        else if(argc==4){
            if((strcmp(argv[1],"-wd"))==0){
                int inputfile;
                if((inputfile = open(argv[3],O_RDONLY)) < 0){
                    close(inputfile);
                    exit();
                }
                int count_buff;
                unsigned char output[1024],data[1024];
                while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
                int newline;
                newline = atoi(argv[2]);
                base64_decode(data, output, strlen((char*)data),1,newline);
                printf(1,"%s\n",output);
                close(inputfile);
                exit();
            }
        else if((strcmp(argv[1],"-we"))==0){
            int inputfile;
            if((inputfile = open(argv[3],O_RDONLY)) < 0){
                close(inputfile);
                exit();
            }
            int count_buff;
            unsigned char output[1024],data[1024];
            while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
            int newline;
            newline = atoi(argv[2]);
            base64_encode(data, output, strlen((char*)data),1,newline);
            printf(1,"%s\n",output);
            close(inputfile);
            exit();  
        }
        else{
            int inputfile;
            if((inputfile = open(argv[3],O_RDONLY)) < 0){
                close(inputfile);
                exit();
            }
            int count_buff;
            unsigned char output[1024],data[1024];
            while ((count_buff = read(inputfile,data,sizeof(data))) > 0);
            int newline;
            
            newline = atoi(argv[2]);
            base64_encode(data, output, strlen((char*)data),1,newline);
            printf(1,"%s\n",output);
            close(inputfile);
            exit();
        }
    }
}
