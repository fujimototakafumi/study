count=0
while true;do
  echo "${1}: ${count}"
  count=$(expr $count + 1)
  sleep 5
done