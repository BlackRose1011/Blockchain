# |blockchain - Основна папка, де знаходиться весь блокчейн 
# | 
# |   |blocks - Папка для зберігання окремих блоків, кожен файл може мати назву,          
# |   |що відповідає номеру наприклад, block1.dat, block2.dat, ...                        
# |   |                                                                                   
# |   |chainstate - Папка, яка містить стан ланцюга, наприклад, індекси та іншу додаткову 
# |   |інформацію, яка може бути потрібною для швидкого доступу до стану блокчейну        
# |   |                                                                                   
# |   |indexes - Папка, де можуть зберігатися індекси для швидкого пошуку даних у         
# |   |блокчейні (наприклад, індекси транзакцій або балансів адрес)                       
# |
# |
# |config - Папка, що містить конфігураційні файли блокчейну
# |database - Папка бази даних, де зберігається весь блокчейн у структурованому форматі
# |logs - Папка для зберігання лог-файлів або інших журналів подій блокчейну
# |info - Папка для зберігання інформації про проект