# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ls-test.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <zboub@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/06 11:49:07 by mcanal            #+#    #+#              #
#    Updated: 2015/02/06 19:09:56 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

echo "\033[36;01m------------  Starting ls-test  ------------\033[0m\n";

cat -e auteur | grep -v $USER >> auteur_test;
grep -R "Created: " * | grep -v $USER >> auteur_test;
grep -R "Updated: " * | grep -v $USER >> auteur_test;
FILE_SIZE=$(du auteur_test | awk '{ print $1 }');
if [ "$FILE_SIZE" = 0 ]; then
	echo "\033[37;01mTesting auteur \033[32;01mOK\033[0m";
else
	echo "\033[37;01mTesting auteur \033[31;01mKO\033[0m";
	cat auteur_test
fi
rm auteur_test;
echo "";

norminette * > norm_test;
cat norm_test |	grep -v "Norme: " | grep -v "Warning: " > norm_test2;
FILE_SIZE=$(du norm_test2 | awk '{ print $1 }');
if [ "$FILE_SIZE" = 0 ]; then
	echo "\033[37;01mTesting norme \033[32;01mOK\033[0m";
else
	echo "\033[37;01mTesting norme \033[31;01mKO\033[0m";
	cat norm_test;
	fi
rm norm_test;
rm norm_test2;
echo "";

make re;

mkdir ls-test-folder;
touch ls-test-folder/ls-test-file;
mkdir ls-test-folder/ls-test-folder-b;
mkdir ls-test-folder/.ls-test-folder2;

for var in '' '-l' '-a' '-r' '-t' '-R' '-arRtl'
do
\ls -1 $var > ../control-ls;
./ft_ls -1 $var > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
	if [ "$FILE_SIZE" = 0 ]; then
		echo "\033[37;01mTesting ls $var : \033[32;01mOK\033[0m";
	else
		echo "\033[37;01mTesting ls $var : \033[31;01mKO\033[0m";
		cat ../ls-diff;
	fi
done

START_PATH=$(pwd);
\ls -1la "$START_PATH" > ../control-ls;
./ft_ls -1la "$START_PATH" > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
if [ "$FILE_SIZE" = 0 ]; then
    echo "\033[37;01mTesting ls -la with absolute path : \033[32;01mOK\033[0m";
else
    echo "\033[37;01mTesting ls -la with absolute path : \033[31;01mKO\033[0m";
    cat ../ls-diff;
fi

for var in 'ls-test-folder' 'ls-test-folder/ls-test-file' 'ls-test-folder/ls-test-file ls-test-folder' 'ls-test-folder ls-test-folder/ls-test-file' 'ls-test-folder/ls-test-file ls-test-folder'
#'/usr/lib' '/dev'
do
\ls -1la $var > ../control-ls;
./ft_ls -1la $var > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
    if [ "$FILE_SIZE" = 0 ]; then
		echo "\033[37;01mTesting ls -la on $var : \033[32;01mOK\033[0m";
    else
        echo "\033[37;01mTesting ls -la on $var : \033[31;01mKO\033[0m";
        cat ../ls-diff;
    fi
done

mkdir ls-test-folder/.ls-test-folder2/.ls-test-folder3;
touch ls-test-folder/.ls-test-folder2/.ls-test-folder3/ls-test-file;
\ls -a1R > ../control-ls;
./ft_ls -a1R > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
if [ "$FILE_SIZE" = 0 ]; then
    echo "\033[37;01mTesting ls -a1R on hidden path : \033[32;01mOK\033[0m";
else
    echo "\033[37;01mTesting ls -a1R on hidden path : \033[31;01mKO\033[0m";
    cat ../ls-diff;
fi

mkdir mydir;
ln -s mydir symdir;
touch mydir/file1;
touch mydir/file2;
touch a;
ln -s a b;
#thanks yyang for symlink test
for var in '' '-l' '-a' '-Rla'
do
\ls -1 $var symdir b > ../control-ls;
./ft_ls -1 $var symdir b > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
if [ "$FILE_SIZE" = 0 ]; then
    echo "\033[37;01mTesting symlink folder (ls $var symdir b) : \033[32;01mOK\033[0m";
else
    echo "\033[37;01mTesting symlink folder (ls $var symdir b) : \033[31;01mKO\033[0m";
    cat ../ls-diff;
fi
done

#thanks yyang again :D
touch -t 201312101830.55 aa;
touch -t 201212101830.55 ab;
touch -t 201412101830.55 ac;
touch -t 201411221830.55 ad;
touch -t 201405212033.55 ae;
touch -t 201409221830.55 af;
touch -t 202007221830.55 ag;
for var in '' '-l' '-a' '-r' '-t' '-rt'
do
\ls -1 $var > ../control-ls;
./ft_ls -1 $var > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
    if [ "$FILE_SIZE" = 0 ]; then
        echo "\033[37;01mTesting old dates (ls $var) : \033[32;01mOK\033[0m";
    else
        echo "\033[37;01mTesting old dates (ls $var) : \033[31;01mKO\033[0m";
        cat ../ls-diff;
    fi
done


#\ls -1la /root > ../control-ls;
#./ft_ls -1la /root > ../test-ls;
#diff ../control-ls ../test-ls > ../ls-diff;
#FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
#if [ "$FILE_SIZE" = 0 ]; then
#    echo "\033[37;01mTesting permission denied (ls -la /root) : \033[32;01mOK\033[0m";
#else
#    echo "\033[37;01mTesting permission denied (ls -la /root) : \033[31;01mKO\033[0m";
#    cat ../ls-diff;
#fi

mkdir no_right;
touch no_right/no_right_file1;
mkdir no_right/still_no_right;
touch no_right/still_no_right/no_right_file2;
chmod 000 no_right;
\ls -1R > ../control-ls;
./ft_ls -1R > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
echo "$FILE_SIZE";
if [ "$FILE_SIZE" = 0 ]; then
    echo "\033[37;01mTesting permission denied (ls -R no_right) : \033[32;01mOK\033[0m";
else
    echo "\033[37;01mTesting permission denied (ls -R no_right) : \033[31;01mKO\033[0m";
    cat ../ls-diff;
fi

\ls -lyeah > ../control-ls;
./ft_ls -lyeah > ../test-ls;
diff ../control-ls ../test-ls > ../ls-diff;
FILE_SIZE=$(du ../ls-diff | awk '{ print $1 }');
echo "$FILE_SIZE";
if [ "$FILE_SIZE" = 0 ]; then
    echo "\033[37;01mTesting flag error (ls -lyeah) : \033[32;01mOK\033[0m";
else
    echo "\033[37;01mTesting flag error (ls -lyeah) : \033[31;01mKO\033[0m";
    cat ../ls-diff;
fi

rm ../control-ls ../test-ls ../ls-diff;
rm -rf ls-test-folder;
rm -rf mydir a b symdir;
rm aa ab ac ad ae af ag;
chmod 777 no_right; rm -rf no_right;
echo ""; echo "";
echo "\033[36;01m---------------  Done  ---------------\033[0m";
