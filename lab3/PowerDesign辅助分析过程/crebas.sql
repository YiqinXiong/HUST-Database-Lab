/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2008                    */
/* Created on:     2020/5/18 12:54:37                           */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Employee') and o.name = 'FK_EMPLOYEE_HIRE_SHOP')
alter table Employee
   drop constraint FK_EMPLOYEE_HIRE_SHOP
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Lack') and o.name = 'FK_LACK_LACK_EMPLOYEE')
alter table Lack
   drop constraint FK_LACK_LACK_EMPLOYEE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Lack') and o.name = 'FK_LACK_LACK2_JUGGLE')
alter table Lack
   drop constraint FK_LACK_LACK2_JUGGLE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Market') and o.name = 'FK_MARKET_MARKET_EMPLOYEE')
alter table Market
   drop constraint FK_MARKET_MARKET_EMPLOYEE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Market') and o.name = 'FK_MARKET_MARKET2_JUGGLE')
alter table Market
   drop constraint FK_MARKET_MARKET2_JUGGLE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Repo') and o.name = 'FK_REPO_REPO_SHOP')
alter table Repo
   drop constraint FK_REPO_REPO_SHOP
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Repo') and o.name = 'FK_REPO_REPO2_JUGGLE')
alter table Repo
   drop constraint FK_REPO_REPO2_JUGGLE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Transfer') and o.name = 'FK_TRANSFER_TRANSFER_SHOP')
alter table Transfer
   drop constraint FK_TRANSFER_TRANSFER_SHOP
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Transfer') and o.name = 'FK_TRANSFER_TRANSFER2_SHOP')
alter table Transfer
   drop constraint FK_TRANSFER_TRANSFER2_SHOP
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Transfer') and o.name = 'FK_TRANSFER_TRANSFER3_JUGGLE')
alter table Transfer
   drop constraint FK_TRANSFER_TRANSFER3_JUGGLE
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Employee')
            and   name  = 'Hire_FK'
            and   indid > 0
            and   indid < 255)
   drop index Employee.Hire_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Employee')
            and   type = 'U')
   drop table Employee
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Juggle')
            and   type = 'U')
   drop table Juggle
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Lack')
            and   name  = 'Lack2_FK'
            and   indid > 0
            and   indid < 255)
   drop index Lack.Lack2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Lack')
            and   name  = 'Lack_FK'
            and   indid > 0
            and   indid < 255)
   drop index Lack.Lack_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Lack')
            and   type = 'U')
   drop table Lack
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Market')
            and   name  = 'Market2_FK'
            and   indid > 0
            and   indid < 255)
   drop index Market.Market2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Market')
            and   name  = 'Market_FK'
            and   indid > 0
            and   indid < 255)
   drop index Market.Market_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Market')
            and   type = 'U')
   drop table Market
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Repo')
            and   name  = 'Repo2_FK'
            and   indid > 0
            and   indid < 255)
   drop index Repo.Repo2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Repo')
            and   name  = 'Repo_FK'
            and   indid > 0
            and   indid < 255)
   drop index Repo.Repo_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Repo')
            and   type = 'U')
   drop table Repo
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Shop')
            and   type = 'U')
   drop table Shop
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Transfer')
            and   name  = 'Transfer3_FK'
            and   indid > 0
            and   indid < 255)
   drop index Transfer.Transfer3_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Transfer')
            and   name  = 'Transfer2_FK'
            and   indid > 0
            and   indid < 255)
   drop index Transfer.Transfer2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Transfer')
            and   name  = 'Transfer_FK'
            and   indid > 0
            and   indid < 255)
   drop index Transfer.Transfer_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Transfer')
            and   type = 'U')
   drop table Transfer
go

/*==============================================================*/
/* Table: Employee                                              */
/*==============================================================*/
create table Employee (
   EID                  int                  not null,
   SID                  int                  not null,
   EType                char(1)              not null default '0'
      constraint CKC_ETYPE_EMPLOYEE check (EType between '0' and '1'),
   PWD                  varchar(32)          not null,
   constraint PK_EMPLOYEE primary key nonclustered (EID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Employee')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'EID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Employee', 'column', 'EID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶԱ��',
   'user', @CurrentUser, 'table', 'Employee', 'column', 'EID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Employee')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'EType')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Employee', 'column', 'EType'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '0Ϊ��Ա��1Ϊ�곤',
   'user', @CurrentUser, 'table', 'Employee', 'column', 'EType'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Employee')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'PWD')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Employee', 'column', 'PWD'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ա����½����',
   'user', @CurrentUser, 'table', 'Employee', 'column', 'PWD'
go

/*==============================================================*/
/* Index: Hire_FK                                               */
/*==============================================================*/
create index Hire_FK on Employee (
SID ASC
)
go

/*==============================================================*/
/* Table: Juggle                                                */
/*==============================================================*/
create table Juggle (
   JID                  int                  not null,
   JName                varchar(128)         not null,
   JNum                 int                  null,
   JAge                 smallint             null
      constraint CKC_JAGE_JUGGLE check (JAge is null or (JAge between 0 and 100)),
   Price                decimal(8,2)         not null
      constraint CKC_PRICE_JUGGLE check (Price >= 0),
   Discount             decimal(3,2)         not null
      constraint CKC_DISCOUNT_JUGGLE check (Discount between 0.00 and 1.00),
   constraint PK_JUGGLE primary key nonclustered (JID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Juggle')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Juggle', 'column', 'JID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ��Ʒ',
   'user', @CurrentUser, 'table', 'Juggle', 'column', 'JID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Juggle')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JName')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Juggle', 'column', 'JName'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '��Ʒ����',
   'user', @CurrentUser, 'table', 'Juggle', 'column', 'JName'
go

/*==============================================================*/
/* Table: Lack                                                  */
/*==============================================================*/
create table Lack (
   LID                  int                  not null,
   EID                  int                  not null,
   JID                  int                  not null,
   LNum                 int                  not null
      constraint CKC_LNUM_LACK check (LNum >= 0),
   LDate                datetime             null,
   constraint PK_LACK primary key (LID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Lack')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'LID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Lack', 'column', 'LID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶȱ����¼',
   'user', @CurrentUser, 'table', 'Lack', 'column', 'LID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Lack')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'EID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Lack', 'column', 'EID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶԱ��',
   'user', @CurrentUser, 'table', 'Lack', 'column', 'EID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Lack')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Lack', 'column', 'JID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ��Ʒ',
   'user', @CurrentUser, 'table', 'Lack', 'column', 'JID'
go

/*==============================================================*/
/* Index: Lack_FK                                               */
/*==============================================================*/
create index Lack_FK on Lack (
EID ASC
)
go

/*==============================================================*/
/* Index: Lack2_FK                                              */
/*==============================================================*/
create index Lack2_FK on Lack (
JID ASC
)
go

/*==============================================================*/
/* Table: Market                                                */
/*==============================================================*/
create table Market (
   MID                  int                  not null,
   EID                  int                  not null,
   JID                  int                  not null,
   MNum                 int                  not null
      constraint CKC_MNUM_MARKET check (MNum >= 0),
   TotalPrice           decimal(8,2)         not null,
   MDate                datetime             null,
   constraint PK_MARKET primary key (MID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Market')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'MID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Market', 'column', 'MID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ�ۻ���¼',
   'user', @CurrentUser, 'table', 'Market', 'column', 'MID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Market')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'EID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Market', 'column', 'EID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶԱ��',
   'user', @CurrentUser, 'table', 'Market', 'column', 'EID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Market')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Market', 'column', 'JID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ��Ʒ',
   'user', @CurrentUser, 'table', 'Market', 'column', 'JID'
go

/*==============================================================*/
/* Index: Market_FK                                             */
/*==============================================================*/
create index Market_FK on Market (
EID ASC
)
go

/*==============================================================*/
/* Index: Market2_FK                                            */
/*==============================================================*/
create index Market2_FK on Market (
JID ASC
)
go

/*==============================================================*/
/* Table: Repo                                                  */
/*==============================================================*/
create table Repo (
   SID                  int                  not null,
   JID                  int                  not null,
   RNum                 int                  not null,
   constraint PK_REPO primary key (SID, JID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Repo')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Repo', 'column', 'JID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ��Ʒ',
   'user', @CurrentUser, 'table', 'Repo', 'column', 'JID'
go

/*==============================================================*/
/* Index: Repo_FK                                               */
/*==============================================================*/
create index Repo_FK on Repo (
SID ASC
)
go

/*==============================================================*/
/* Index: Repo2_FK                                              */
/*==============================================================*/
create index Repo2_FK on Repo (
JID ASC
)
go

/*==============================================================*/
/* Table: Shop                                                  */
/*==============================================================*/
create table Shop (
   SID                  int                  not null,
   SName                varchar(128)         not null,
   CityName             varchar(128)         not null,
   constraint PK_SHOP primary key nonclustered (SID)
)
go

if exists (select 1 from  sys.extended_properties
           where major_id = object_id('Shop') and minor_id = 0)
begin 
   declare @CurrentUser sysname 
select @CurrentUser = user_name() 
execute sp_dropextendedproperty 'MS_Description',  
   'user', @CurrentUser, 'table', 'Shop' 
 
end 


select @CurrentUser = user_name() 
execute sp_addextendedproperty 'MS_Description',  
   '�����ŵ��', 
   'user', @CurrentUser, 'table', 'Shop'
go

/*==============================================================*/
/* Table: Transfer                                              */
/*==============================================================*/
create table Transfer (
   TID                  int                  not null,
   FSID                 int                  not null,
   TSID                 int                  not null,
   JID                  int                  not null,
   TNum                 int                  not null
      constraint CKC_TNUM_TRANSFER check (TNum >= 0),
   TDate                datetime             null,
   TStatus              char(1)              not null default '2'
      constraint CKC_TSTATUS_TRANSFER check (TStatus between '0' and '2'),
   constraint PK_TRANSFER primary key (TID)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Transfer')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'TID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'TID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ������¼',
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'TID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Transfer')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'JID')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'JID'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Ψһ��ʶ��Ʒ',
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'JID'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Transfer')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'TStatus')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'TStatus'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '0��ʾ���ܾ���1��ʾͬ�⣬2��ʾ�ȴ�',
   'user', @CurrentUser, 'table', 'Transfer', 'column', 'TStatus'
go

/*==============================================================*/
/* Index: Transfer_FK                                           */
/*==============================================================*/
create index Transfer_FK on Transfer (
FSID ASC
)
go

/*==============================================================*/
/* Index: Transfer2_FK                                          */
/*==============================================================*/
create index Transfer2_FK on Transfer (
TSID ASC
)
go

/*==============================================================*/
/* Index: Transfer3_FK                                          */
/*==============================================================*/
create index Transfer3_FK on Transfer (
JID ASC
)
go

alter table Employee
   add constraint FK_EMPLOYEE_HIRE_SHOP foreign key (SID)
      references Shop (SID)
go

alter table Lack
   add constraint FK_LACK_LACK_EMPLOYEE foreign key (EID)
      references Employee (EID)
go

alter table Lack
   add constraint FK_LACK_LACK2_JUGGLE foreign key (JID)
      references Juggle (JID)
go

alter table Market
   add constraint FK_MARKET_MARKET_EMPLOYEE foreign key (EID)
      references Employee (EID)
go

alter table Market
   add constraint FK_MARKET_MARKET2_JUGGLE foreign key (JID)
      references Juggle (JID)
go

alter table Repo
   add constraint FK_REPO_REPO_SHOP foreign key (SID)
      references Shop (SID)
go

alter table Repo
   add constraint FK_REPO_REPO2_JUGGLE foreign key (JID)
      references Juggle (JID)
go

alter table Transfer
   add constraint FK_TRANSFER_TRANSFER_SHOP foreign key (FSID)
      references Shop (SID)
go

alter table Transfer
   add constraint FK_TRANSFER_TRANSFER2_SHOP foreign key (TSID)
      references Shop (SID)
go

alter table Transfer
   add constraint FK_TRANSFER_TRANSFER3_JUGGLE foreign key (JID)
      references Juggle (JID)
go

