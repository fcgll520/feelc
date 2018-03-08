drop table if exists profile;

create table profile
(
	id	int unsigned not NULL,
	index(id)
);

insert into profile(id) values(1);
insert into profile(id) values(2);
insert into profile(id) values(3);
