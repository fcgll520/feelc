drop table if exists profile_contact;

create table profile_contact
(
	profile_id	int unsigned not NULL,
	service		char(20) not NULL,
	contact_name	char(25) not NULL,
	index(profile_id)
);

insert into profile_contact(profile_id, service, contact_name) values(1, "AIM", "user1-aimid");
insert into profile_contact(profile_id, service, contact_name) values(1, "MSN", "user1-msnid");

insert into profile_contact(profile_id, service, contact_name) values(2, "AIM", "user2-aimid");
insert into profile_contact(profile_id, service, contact_name) values(2, "MSN", "user2-msnid");
insert into profile_contact(profile_id, service, contact_name) values(2, "Yahoo", "user2-yahooid");

insert into profile_contact(profile_id, service, contact_name) values(4, "Yahoo", "user4-yahooid");
