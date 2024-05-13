#include<stdio.h>
#include<string.h>

long long count = 0;

void searchnum(char* word, char* std, int temp, long long min, long long max) {
	int i, j;
	int word_len = strlen(word);
	int std_len = strlen(std);
	
	//이 경우는 의미 없으므로 break
	if (count > max) {
		return;
	}

	if (temp == 0) {
		for (j = 0; j < word_len; j++) {
			if (count >= min - 1 && count <= max - 1) {
				printf("%c", word[j]);
			}
			count++;
		}
		return;
	}

	for (i = 0; i < std_len; i++) {
		//$일때 다시 재귀진행
		if (std[i] == '$') {
			searchnum(word, std, temp - 1, min, max);
		}
		else {
			if (count >= min - 1 && count <= max - 1) {
				printf("%c", std[i]);
			}
			count++;
		}
	}
}


int main(void) {
	char word[51], s[51];
	int cnt, dollar = 0, nodollar = 0, temp = 0;
	long long word_len, max, min, i, check = 0;
	scanf("%s", word);
	scanf("%s", s);
	scanf("%d", &cnt);
	scanf("%lld %lld", &min, &max);
	// $의 개수와 아닌것의 개수 구하기
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == '$') {
			dollar++;
		}
		else {
			nodollar++;
		}
	}
	
	word_len = strlen(word);
	//문제에서 주어진 횟수만큼 했을 때 길이가 1000000099가 넘어가는지 확인
	while (temp < cnt) {
		if (word_len > 1000000099) {
			word_len = 1000000099;
			break;
		}
		word_len = word_len * dollar + nodollar;
		temp++;
	}
	
	//길이가 최소 출력 index보다도 작으면 max-min개 만큼 -출력
	if (word_len < min) {
		for (i = min; i < max; i++) {
			printf("-");
		}
		check = 1;
	}
	else {
		searchnum(word, s, temp, min, max);
	}

	// 인덱스가 남을 때는 최대 길이 - max만큼 -출력
	if (count < max && check == 0) {
		for (i = 0; i < (max - word_len); i++) {
			printf("-");
		}
	}

    printf("\n");

	return 0;
}