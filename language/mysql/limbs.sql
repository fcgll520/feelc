drop table if exists limbs;
create table limbs 
(
	thing varchar(20),
	legs int,
	arms int
);

insert into limbs (thing, legs, arms) values("human", 2, 2);
insert into limbs (thing, legs, arms) values("insect", 6, 0);
insert into limbs (thing, legs, arms) values("squid", 0, 10);
