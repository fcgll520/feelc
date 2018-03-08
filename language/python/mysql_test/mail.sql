drop table if exists mail;

create table mail
(
    t       datetime, #消息发送时间
    srcuser char(8),  #发送者
    srchost char(20),
    drcuser char(8),  #接收者
    drchost char(20),
    size    bigint,   #消息的字节大小
    index(t)
);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-06-11 10:15:08", "barb", "saturn", "tricia", "mars", 100);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-07-11 10:15:08", "tricia", "mars", "gene", "venus", 200);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-08-11 10:15:08", "phil", "mars", "phil", "saturn", 300);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-09-11 10:15:08", "barb", "saturn", "tricia", "venus", 400);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-10-11 10:15:08", "gene", "venus", "barb", "venus", 500);

insert into mail(t, srcuser, srchost, drcuser, drchost, size) \
    values("2006-11-11 10:15:08", "phil", "mars", "tricia", "saturn", 600);
