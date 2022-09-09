- 수정된 사항
1. excute_pipe 파일 만들어서 파이프 실행 따로 분리
2. syntax error의 exit code를 258로 설정
3. heredoc용 시그널 처리 수정(클러스터 맥 기준으로 변경, 클러스터 맥은 히어독 exit가 1)
4. excute_bracket 현재 메인문에 맞춰서 수정

- 자잘한 처리
make command -> make_char_arr로 변경
hd_sig signal 함수에 넣음
간단한 norm 수정 (마지막줄 스페이스, 함수 정렬, 다 처리된 주석)

by yehyun