# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ls.sh                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/16 08:41:02 by mcanal            #+#    #+#              #
#    Updated: 2015/01/16 09:56:32 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#make re;
echo "\033[36;01mft_ls\033[0m (test)";
./ft_ls -1 $1 $2 $3 $4 $5 $6 $7 $8 $9 > ../test;
cat ../test
echo "";
echo "\033[36;01mls\033[0m (control)";
\ls -1 $1 $2 $3 $4 $5 $6 $7 $8 $9 > ../control;
cat ../control
diff ../control ../test > ../dif;
echo "";
FILE_SIZE=$(du ../dif | awk '{ print $1 }');
    if [ "$FILE_SIZE" = 0 ]; then
        echo "\033[32;01mOK\033[0m";
	else
		echo "\033[31;01mKO\033[0m";
		cat ../dif;
fi
rm ../test ../control ../dif;
