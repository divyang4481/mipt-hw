

# STL manpages на Ubuntu #

## Как установить ##

sudo apt-get install libstdc++6-4.6-doc

Если такой версии нет, вызываем сначала так:

apt-cache search libstdc++ | grep doc

Смотрим, которые версии доступны для Вашего дистрибутива и устанавливаем.

## Как пользоваться ##

Чтобы узнать, в каком разделе лежат необхидимые Вам маны, можно вызвать:

apropos vector

Либо так:

man -k vector

Среди прочего выведется что-то вроде:
std\_vector (3cxx)    - (unknown subject)

Это значит, что маны по std::vector лежат в разделе 3cxx. Скорее всего, у Вас также.

Теперь справку можно получить так:

man 3cxx std\_vector

man 3cxx std\_map