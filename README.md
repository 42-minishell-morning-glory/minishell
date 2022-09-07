- solved issue
1. 시그널 따로 지정하지 않고 exit code 정상화 및 좀비자식 정상 종료 -> 파이프를 자식이 자식을 생성하는 방식으로 변경
2. 따라서 yes | head -1 이것도 잘 됨.
3. heredoc과 pipe 같이 있을 때, 아웃파일로 데이터 잘 옮겨짐. 임시로 일단 heredoc > 지워둠.

- known issue
1. asdasdsa | ls처럼 올바르지 않은 명령어 입력했을 때, 앞 명령어에 대한 에러 메세지 출력이 readline 프롬프트와 같이 나옴.
2. << END | << END 처럼 파이프로 heredoc 2개 이상 나올 때, 앞에꺼 하나만 처리하면 파이프 프로세스가 종료됨.
3. cat | cat | cat | echo hi -> hi터미널에 출력되고 엔터 세번누르면 종료 bash에서는 파이프가 뒤부터 닫힘 echo하면 read pipe가 닫힘 | 미니쉘에서는 파이프가 앞에서 부터 닫힘 |
4. echo -n > outfile 하면 아웃파일로 출력이 안감...