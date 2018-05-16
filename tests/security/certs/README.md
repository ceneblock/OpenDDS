# Notes on file generation

## Generate CA Authority and related files

  ```
  openssl genrsa -out opendds_identity_ca_private_key.pem 2048
  openssl req -config identity_ca_openssl.cnf -new -key opendds_identity_ca_private_key.pem -out opendds_identity_ca.csr
  openssl x509 -req -days 3650 -in opendds_identity_ca.csr -signkey opendds_identity_ca_private_key.pem -out opendds_identity_ca_cert.pem
  touch index.txt; echo "01" > serial
  ```

## Generate Mock Participants

  For the first mock-participant the same config file "identity\_ca\_openssl.cnf" was used to quickly generate a participant
  using the same company information as the CA cert.
  ```
  openssl genrsa -out opendds_participant_private_key.pem 2048
  openssl req -config identity_ca_openssl.cnf -new -key opendds_participant_private_key.pem -out opendds_participant.csr
  openssl ca -config identity_ca_openssl.cnf -days 3650 -in opendds_participant.csr -out opendds_participant_cert.pem
  ```

  For the second mock-participant, no config file is passed in so it is filled with fictitious company information. This
  serves as a more realistic scenario in the unit tests. Only the csr-generation (step 2) below is different than above.
  ```
  openssl genrsa -out opendds_participant_private_key.pem 2048
  openssl req -new -key opendds_participant_private_key.pem -out opendds_participant.csr
  openssl ca -config identity_ca_openssl.cnf -days 3650 -in opendds_participant.csr -out opendds_participant_cert.pem
  ```

  Note: since the files for each participant have the same name, they were moved into the appropriate directories before
  	generating the next pair of keys.