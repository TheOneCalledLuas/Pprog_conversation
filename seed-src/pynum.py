num = 1
found =0
content = ""
new_line = ""
filename = input("ingresa el nombre del archivo: ")

#Fixes the file.
with open("tester.txt","r",encoding="UTF-8") as file:
    for line in file:
        found = line.find("==")
        if found != -1:
            new_line = ""
            new_line += line[0:found+2]
            new_line += f" {str(num)}"
            if num<10:
                new_line += line[found+4:]
            else:
                new_line += line[found+5:]
            num += 1
            content = content + new_line
        else:
            content = content + line

with open("result.txt","w",encoding="UTF-8") as file:
    file.write(content)

print(content)

