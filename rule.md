< infile cat -e | cat -e | cat -e && ls > outfile 
< infile cat -e | cat -e | (cat -e && ls) > outfile 
< infile cat -e | (ls | cat -e) && ls > outfile 

- || 에서 둘 다 참이면, 앞에 것만 실행
- || 에서 앞 참 뒤 거짓, 앞에 것만 실행
- || 에서 앞 거짓 뒤 참, 앞 에러 메세지 출력 후 뒤 실행
- () 안에 여러 명령어가 있을 경우, 먼저 입력 가져가는 애가 임자

<quote 규칙>
               
"
> \"'\"'"