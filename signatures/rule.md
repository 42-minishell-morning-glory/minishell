< infile cat -e | cat -e | cat -e && ls > outfile 
< infile cat -e | cat -e | (cat -e && ls) > outfile 
< infile cat -e | (ls | cat -e) && ls > outfile 

<!--- 문법 검사 먼저(split 시 문제 생길 것들)
	- > >> 
	- | ||
	- >>>-->
- strncmp로 검사 
- split에서 charset도 저장
	- | || // < << 
	- & 하나는 쓸 일 없음
- || 에서 둘 다 참이면, 앞에 것만 실행
- || 에서 앞 참 뒤 거짓, 앞에 것만 실행
- || 에서 앞 거짓 뒤 참, 앞 에러 메세지 출력 후 뒤 실행
- () 안에 여러 명령어가 있을 경우, 먼저 입력 가져가는 애가 임자

<quote 규칙>
               
"
> \"'\"'"

<괄호 처리할 때 규칙>
- 괄호 앞뒤로 명령어가 있으면, 

"ls || "
=> 따옴표안에 파이프나 리다이렉션 등 들어가면 터짐 (해결)


<redirection 규칙>

1. 	무조건 오른쪽 노드에서 첫 번째 리스트는 파일 / 나머지는 명령어
2. 미리 open금지 (fd초과)
해야할일
	엑세큐트구현시 잘 할 수 있게

	최말단 구현 

<처리해야 할 에러 목록>
1. 파이프 개만흥ㅁ | 실제 bash message =>  bash: fork: Resource temporarily unavailable | 렉싱단계에서 전체 fork개수 파악
2. 리다이렉션이랑 와일드카드 붙어있음

파이프 => input & here-doc
	output은 모르겠음

<built-in 함수>
1. env을 건드는 함수인데 파이프이면 들어가서 실행하고 (영향이 없음)

<알려진 오류>
1. 표준입력 상태에서 ctrl c 누르면 모닝쉘 두번 나옴

2. exit hihi => numeric arument required
			==> exit code 255
3. exit 122 21321 => too many arguments
			==> 1인데 exit 안됨
4. exit hihi bye => numeric arument required
			==> exit code 255
5. "< ("=> systax error near unexpected token '('
			==> exit code 258
6. 표준입력 받는 중에 ctrl + \ 했을 때 bash랑 다름 (서브젝트 다시 확인 필요함)
