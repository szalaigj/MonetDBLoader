-- the reference genome storage:
CREATE TABLE ref(
refID int NOT NULL,
pos bigint NOT NULL,
refNuc char NULL,
CONSTRAINT PK_ref PRIMARY KEY
(
refID,
pos
)
);

-- the binary bulk loading statement with monetdb (admin) user:
copy binary into ref from ('path_to_/ref_refID.dat', 'path_to_/ref_pos.dat', 'path_to_/ref_refNuc.dat');
